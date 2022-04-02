# 自分用環境構築
## 自分用設定ファイル読み込み

```bash
 echo source ~/bin/myzshrc >> ~/.zshrc
 source ~/.zshrc
```

## brew入れる

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## gcc(g++)入れる

```bash
brew install gcc
```


brewでインストールする前も後も``gcc``,``g++``コマンドはそれぞれgccのフリをしたclangが出てくるため、シンボリックリンクを作って（clangの居場所の)``/usr/bin/``より先に読み込まれる場所に置いておく。場所はとりあえず``/usr/local/bin``へ。（myzshrcには追加済み）

zshrcに書きたい用
```bash
echo export PATH="/usr/local/bin:$PATH" >> ~/.zshrc
```


実行ファイルの場所の確認(M1のbrewは``/opt/homebrew/``にインストールするようになった)

一応バージョン確認しておく
```bash
ls /opt/homebrew/bin/ | grep g++
#M1なので名前の長い方が多分ネイティブ
aarch64-apple-darwin21-g++-11
g++-11
```

```bash
sudo ln -s /opt/homebrew/bin/aarch64-apple-darwin21-g++-11 /usr/local/bin/g++
```

お遊び用で<bits/std++>を使いたいだけなのでg++だけでよい


## zshいい感じに
```bash
brew install zsh-completions        #補完
brew install zsh-git-prompt         #リポジトリ表示してくれる
brew install zsh-autosuggestions    #続きが見える
```