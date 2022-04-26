$> echo $PWD
/Users/jforner/Documents/42/minishell
$> unset PWD
$> echo $PWD

$> cd ..
$> echo $PWD
/Users/jforner/Documents/42
$> env | grep PWD
$> env | grep _=
_=./minishell
$> export
declare -x TERM_PROGRAM="vscode"
declare -x TERM="xterm-256color"
declare -x SHELL="/bin/zsh"
declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n0000jnc0004db/T/"
declare -x Apple_PubSub_Socket_Render="/private/tmp/com.apple.launchd.7iPZ0Vycvx/Render"
declare -x TERM_PROGRAM_VERSION="1.59.0"
declare -x ORIGINAL_XDG_CURRENT_DESKTOP="undefined"
declare -x USER="jforner"
declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.LM76KQKy6K/Listeners"
declare -x __CF_USER_TEXT_ENCODING="0x11AB:0x0:0x0"
declare -x PATH="/Users/jforner/.brew/bin:/Users/jforner/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"
declare -x LANG="en_US.UTF-8"
declare -x XPC_FLAGS="0x0"
declare -x XPC_SERVICE_NAME="0"
declare -x SHLVL="2"
declare -x HOME="/Users/jforner"
declare -x VSCODE_GIT_ASKPASS_MAIN="/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js"
declare -x LOGNAME="jforner"
declare -x VSCODE_GIT_IPC_HANDLE="/var/folders/zz/zyxvpxvq6csfxvn_n0000jnc0004db/T/vscode-git-cd525feaa5.sock"
declare -x VSCODE_GIT_ASKPASS_NODE="/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Renderer).app/Contents/MacOS/Code Helper (Renderer)"
declare -x GIT_ASKPASS="/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh"
declare -x COLORTERM="truecolor"
declare -x _="./minishell"
declare -x OLDPWD=""
$> echo $OLDPWD

$> cd minishell/
$> echo $OLDPWD
/Users/jforner/Documents/42
$> env | grep PWD
OLDPWD=/Users/jforner/Documents/42
$> export PWD
$> env | grep PWD
OLDPWD=/Users/jforner/Documents/42
PWD=/Users/jforner/Documents/42/minishell
$> echo $PWD
/Users/jforner/Documents/42/minishell
$> echo $PWD ===== $OLDPWD
/Users/jforner/Documents/42/minishell ===== /Users/jforner/Documents/42
$> unset PWD OLDPWD
$> echo $PWD ===== $OLDPWD
=====
$> cd ..
$> cd
$> pwd
/Users/jforner
$> echo $PWD ===== $OLDPWD
/Users/jforner ===== /Users/jforner/Documents/42
$> env | grep PWD
$> echo $.

$> echo $_
./minishell
$> 