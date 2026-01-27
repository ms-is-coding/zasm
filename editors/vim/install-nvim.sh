#!/bin/bash
VIM_DIR="$HOME/.config/nvim"

mkdir -p "$VIM_DIR/syntax" "$VIM_DIR/ftdetect" "$VIM_DIR/ftplugin"

ln -sf "$(pwd)/syntax/zasm.vim" "$VIM_DIR/syntax/zasm.vim"
ln -sf "$(pwd)/ftdetect/zasm.vim" "$VIM_DIR/ftdetect/zasm.vim"

echo "Zasm Vim files linked to $VIM_DIR"
