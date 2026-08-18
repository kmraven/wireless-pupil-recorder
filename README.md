# XIAO ESP32S3 Sense Video Recorder

Seeed Studio XIAO ESP32S3 Senseで、JPEGフレームをAVIとしてmicroSDカードへ録画するスケッチです。録画しながら、必要に応じてローカルWi-Fi経由でライブ映像やSDカード内のファイルを確認できます。

## 基本的な使い方

1. `config.example.txt`を`config.txt`という名前でmicroSDカードのルートへコピーします。
2. 下記の順序を変えずに設定値を編集します。
3. microSDカードをXIAO ESP32S3 Senseへ挿入して起動します。
4. 停止するときはBOOTボタンを1.5秒長押しします。LEDが点滅したら録画ファイルとSDカードが閉じられており、電源を外せます。

`config.txt`がない場合は、Wi-Fi OFFを初期値とするファイルをSDカードへ自動生成します。

## config.txt

設定は1項目1行で、行の順序に意味があります。値の後ろには`//`でコメントを書けます。

| 行 | 設定 | 内容 |
|---:|---|---|
| 1 | camera name | ファイル名とmDNSホスト名。英数字とハイフンを推奨 |
| 2 | frame size | `11`はHD（1280×720） |
| 3 | recording length | AVI 1本の録画秒数 |
| 4 | recording count | 録画するAVIの本数。`0`は無制限 |
| 5 | recording interval | 録画フレーム間隔（ms）。`0`は最速 |
| 6 | speed multiplier | 再生速度倍率。`1`は実時間 |
| 7 | stream interval | ライブ映像のフレーム間隔（ms）。`0`は最速 |
| 8 | timezone | 例：`GMT` |
| 9 | wifi mode | `0`=OFF、`1`=STA、`2`=AP |
| 10 | Wi-Fi SSID | STAでは接続先SSID、APではESP32が作るSSID |
| 11 | Wi-Fi password | STAでは接続先パスワード、APでは8～63文字のAPパスワード |
| 12 | STA IP mode | `0`=DHCP/mDNS、`1`=固定IPv4 |
| 13 | static IPv4 | 固定IPモードで使うESP32のアドレス |
| 14 | gateway | 固定IPモードのゲートウェイ |
| 15 | subnet mask | 固定IPモードのサブネットマスク |
| 16 | DNS server | 固定IPモードのDNSサーバー |

直前の16行形式（recording countが11行目）と、それ以前の旧形式も読み込めます。旧形式では8行目が`ssid1234`ならWi-Fi OFF、`ap`または`wifiman`ならAP、それ以外ならSTAとして扱います。新しく作るconfigでは上表の形式を使用してください。

## Wi-Fiモードと接続先

### 0: OFF

Wi-FiとWebサーバーを起動しません。SDカードだけで運用するときの省電力設定です。10～16行目は使用されませんが、行位置を保つため削除しないでください。

### 1: STA（ローカルWi-Fiへ接続）

XIAO ESP32S3 Senseは2.4 GHz Wi-Fiへ接続します。PCも同じローカルネットワークへ接続してください。

DHCP/mDNSを使う例：

```text
desklens  // camera name
11  // frame size
1800  // recording length
0  // recording count
...
1  // wifi mode
YOUR_2G_WIFI_SSID
YOUR_WIFI_PASSWORD
0  // STA IP mode: DHCP/mDNS
```

PCで開くアドレスは、1行目から決まります。

```text
http://desklens.local/
```

mDNSを通さないネットワークや、常に数値IPで接続したい場合は固定IPを使います。

```text
1  // STA IP mode: static IPv4
192.168.1.123  // ESP32 address
192.168.1.1  // gateway
255.255.255.0  // subnet mask
192.168.1.1  // DNS
```

この例の接続先は`http://192.168.1.123/`です。固定IPは使用中のLANと同じサブネットにし、ほかの機器やルーターのDHCP割り当てと重複させないでください。

STA接続に失敗してもAPへ自動移行しません。意図しない無線ネットワークを作らず、30秒後にSTA接続を再試行します。

### 2: AP（ESP32がWi-Fi親機になる）

10、11行目で指定したSSIDとパスワードのネットワークをESP32が作ります。PCをそのSSIDへ接続し、次を開きます。

```text
http://192.168.4.1/
```

APのIPはコードで`192.168.4.1`へ固定されています。

## Web画面

`ADDRESS`を上記で決まるホスト名またはIPに置き換えます。

| 機能 | URL |
|---|---|
| 操作画面 | `http://ADDRESS/` |
| 静止画 | `http://ADDRESS/capture` |
| MJPEGライブ映像 | `http://ADDRESS:81/stream` |
| 2つ目のライブ映像 | `http://ADDRESS:82/stream` |
| SDファイル管理 | `http://ADDRESS:8080/` |

Web画面に認証はありません。信頼できるローカルネットワーク内だけで使用し、インターネットへのポート開放はしないでください。

## 物理操作

- BOOTボタン：1.5秒長押しで安全停止。LED点滅後に電源を外せます。
- GPIO43：未接続/HIGHで録画、GND/LOWで録画停止。
- GPIO44：Wi-FiモードがSTAまたはAPのとき、未接続/HIGHでWi-Fi起動、GND/LOWでWi-Fi停止。

GPIO44を未接続にすると内部プルアップによりWi-Fiが起動します。常にWi-Fiを使わない場合は、GPIO操作ではなく`wifi mode = 0`を設定してください。

## 注意事項

- 録画中の突然の電源断は、AVIやFATファイルシステムを破損させる可能性があります。通常はBOOTボタンによる安全停止を使用してください。
- ライブ映像の閲覧中はWi-Fi送信と画像コピーが増えるため、Wi-Fi OFF時より消費電力が増えます。
- `config.txt`にはWi-Fiパスワードが入るためGit管理対象外です。公開用には`config.example.txt`を使用してください。
