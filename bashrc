subst w: ~/local

# I keep mistyping these
alias la=ls

alias gs='git status --short --branch'
alias gl='git lg'
alias gu='git pull'
alias gp='git push'

#export PS1='\e[0m \[\033]0;$TITLEPREFIX:$PWD\[\007\]\n\[\033[32m\]\! \[\033[33m\]\w\[\033[36m\]`__git_ps1`\[\033[0m\]\n\[\e[1m\]λ\[\e[0m\] \e[2m'
export PS1='\e[0m \[\033]0;$TITLEPREFIX:$PWD\[\007\]\n\e[0m\]\! \[\033[33m\]\w\[\033[36m\]`__git_ps1`\[\033[0m\]\n\[\e[2m\]λ \e[0m\] \e[1m'

export PS2='-->'
trap 'echo -n -e "\e[0m"' DEBUG

# ADB
#export PATH=$PATH:'/c/Program\ Files/Unity/2019.3.6f1/Editor/Data/PlaybackEngines/AndroidPlayer/SDK/platform-tools'
export PATH=$PATH:~/bin/platform-tools_r30.0.5-windows/platform-tools

# HLA https://www.plantation-productions.com/Webster/HighLevelAsm/WinDownload.html
export PATH=$PATH:/c/bin/hla

WORK_LETTER=w
WORK_ROOT=/$WORK_LETTER
WORK_NAME='work'
WORK_DIR=$WORK_ROOT

export WORK_ROOT
export WORK_LETTER
export WORK_NAME
export WORK_DIR

alias yt='youtube-dl.exe'

. $WORK_ROOT/bin/startup

cd ~/repos/ChessClock

alias 'cpi'='adb connect 192.168.0.17:5555'

alias 'sshpi'='ssh pi@192.168.12'

