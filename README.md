# TightVNC Viewer fork for NEC

tightvnc fork版本，主要修改 viewer 配合连接 NEC。

本仓库基于 TightVNC 2.8.88 GPL 源码，当前只发布 Windows Viewer。它保持普通 TightVNC/VNCAuth 和原有 File Transfer 行为，并增加：

- Tight Security 的 UnixLogin 子认证（code `129`，`TGHT` / `ULGNAUTH`）。
- 独立的 Username + 完整 Password 登录框，密码不再受 VNCAuth 的 8 字节限制。
- `-username=...` 与现有 `-password=...` 组合，可在当前进程内提供 UnixLogin 凭据。
- 根据双方 MD5 capability 自动禁用 Append；没有 MD5 时上传、下载始终发送 offset `0`。
- 兼容 NEC 通过 TightVNC File Transfer 映射到资产 SFTP 的能力声明。

## 构建

推荐使用 Visual Studio 2017 打开 `tightvnc2017.sln`，构建 `tvnviewer` 的 `Release|Win32` 或 `Release|x64`。使用 Visual Studio 2022 时可以在命令行临时重定向工具集：

```bat
msbuild tightvnc2017.sln /t:tvnviewer /m /p:Configuration=Release /p:Platform=Win32 /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0
msbuild tightvnc2017.sln /t:tvnviewer /m /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0
```

GitHub Actions 会同时检查 Win32 和 x64，并上传 `tvnviewer.exe` 构建产物。

## 使用

正常输入 NEC 地址。NEC 声明 UnixLogin 时，Viewer 会显示 Username/Password 对话框；Username 填 connection token ID，Password 填 token value。连接只声明 VNCAuth 的普通服务器时，仍显示原有密码框。

也可以使用命令行：

```bat
tvnviewer.exe nec.example.com::5900 -username=TOKEN_ID -password=TOKEN_VALUE
```

命令行参数可能被本机其他进程读取，优先使用交互登录框。完整 UnixLogin 密码不会写入 Viewer history、注册表或 `.vnc` options file。

> Tight UnixLogin 本身不提供传输加密。仅应在受信任内网或 VPN 中使用；不要把该端口直接暴露到不可信网络。

## 上游与许可

上游来源和 fork 边界见 [UPSTREAM.md](UPSTREAM.md)。本仓库按 GNU GPL v2 or later 分发，见 [LICENSE](LICENSE)。
