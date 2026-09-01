# Firmware Development

## mavlink-cpp

MAVLinkのメッセージを送受信するためのC++ライブラリです。MAVLinkメッセージの定義、wire-formatのparser/packerが実装されています。[mavlink-dialect](https://github.com/TeamMeltingPoppo/mavlink-dialect)のMAVLinkメッセージ定義から自動生成されています。MAVLinkのC++ライブラリは、[mavlink-cppのReleases](https://github.com/TeamMeltingPoppo/mavlink-cpp/releases)からダウンロードできます。

PlatformIOのプロジェクトでは`platformio.ini`の`lib_deps`に`mavlink-cpp`を追加することで、MAVLinkのC++ライブラリを利用できます。

```ini
lib_deps = 
    https://github.com/TeamMeltingPoppo/mavlink-cpp/releases/download/0.5.0/mavlink-platformio.zip
```

framework、platformに依らず使うことができます。`mavlink-cpp`の使い方は、[mavlinkのCライブラリの使い方](https://mavlink.io/en/mavgen_c/)と同じです。