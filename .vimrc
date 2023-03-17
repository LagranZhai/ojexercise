set fileencodings=utf-8,gb2312,gb18030,gbk,ucs-bom,cp936,latin1
set enc=utf8
set fencs=utf8,gbk,gb2312,gb18030
"set nu                " 显示行号
colorscheme desert    " 颜色主题
""syntax on             " 打开语法高亮
""set nu                      " 显示行号
""set tabstop=4               " 设置软制表符宽度为4
""set softtabstop=4           " 设置软制表符宽度为4
""set shiftwidth=4            " 设置缩进的空格数为4
""set autoindent              " 设置自动缩进：即每行的缩进值与上一行相等
set cindent                 " 使用 C/C++ 语言的自动缩进方式
set cursorline              " 突出显示当前行
set expandtab               " 空格代替制表符
set showmatch               " 光标遇到圆括号、方括号、大括号时，自动高亮对应的另一个圆括号、方括号和大括号
set ruler                   " 在状态栏显示光标的当前位置（位于哪一行哪一列）
 
set guifont=Consolas:h15    " 设置字体和字体大小
"colorscheme molokai         " 设置主题为molokai

set nobackup                " 取消备份文件
                            " 默认情况下，文件保存时，会额外创建一个备份文件，它的文件名是在原文件名的末尾，再添加一个波浪号~
setlocal noswapfile         " 不创建交换文件。交换文件主要用于系统崩溃时恢复文件，文件名的开头是.、结尾是.swp
set noundofile              " 取消生成un文件
 
set hlsearch                " 设置高亮显示搜索字符串
set showmode                " 在底部显示，当前处于命令模式还是插入模式
set showcmd                 " 命令模式下，在底部显示，当前键入的指令。比如输入快捷键将在底部显示具体命令
set t_Co=256                " 启用256色
set noerrorbells            " 出错时不要发出响声
" 高亮显示
syntax enable
filetype indent on

autocmd GUIEnter * simalt ~x
colorscheme desert
syntax on

filetype indent on
set autoindent
set tabstop=4
set shiftwidth=4
set softtabstop=4

set nocompatible
set backspace=indent,eol,start

set number
set laststatus=2
set statusline=%F%h%m%r%=Line\ %l/%L,\ Column\ %c
inoremap ( ()<LEFT>
inoremap [ []<LEFT>
inoremap { {}<LEFT>
inoremap ' ''<LEFT>
inoremap " ""<LEFT>


inoremap <CR> <c-r>=AutoEnter()<CR>
func! AutoEnter()
	if (getline('.')[col(".") - 2] == '{' && getline('.')[col(".") - 1] == '}')
		return "\<CR>\<UP>\<END>\<CR>"
	else
		return "\<CR>"
	endif
endfunc

func SkipPair()  
    if getline('.')[col('.') - 1] == ')' || getline('.')[col('.') - 1] == ']' || getline('.')[col('.') - 1] == '"' || getline('.')[col('.') - 1] == "'" || getline('.')[col('.') - 1] == '}'  
            return "\<ESC>la"  
    else  
        return "\t"  
    endif  
endfunc
inoremap <TAB> <c-r>=SkipPair()<CR>

autocmd BufNewFile *.cpp exec ":call SetTitle()" 
func SetTitle()
call append(line(".")+3, "#include<bits/stdc++.h>")
		call append(line(".")+4, "using namespace std;")
		call append(line(".")+5, "")
		call append(line(".")+6, "int main(")
		call append(line(".")+7, "{")
   call append(line(".")+8, "	   ios::sync_with_stdio(false);")
   call append(line(".")+9, "	   return 0;")
		call append(line(".")+10, "}")
   autocmd BufNewFile * normal G
endfunc 
map <F5> :call Debug()<CR>
func! Debug()
	exec "w"
	exec "!g++ % -g -o ~/temp/bin/%<.out"
	exec "!gdb %"
endfunc
map <F8> :call Compile()<CR>
func! Compile()
	exec "w"
	exec "!g++ % -Wall -o ~/temp/bin/%<.out"
endfunc

map <F9> :call Coompile()<CR>
func! Coompile()
	exec "w"
	exec "!g++ % -Wall -O2 -o ~/temp/bin/%<.out"
endfunc

map <F10> :call Run()<CR>
func! Run()
	exec "!~/temp/bin/%<.out"
endfunc

map <F11> :call CompileAndRun()<CR>
func! CompileAndRun()
	exec "call Compile()"
	exec "call Run()"
endfunc

map <F12> :call CoompileAndRun()<CR>
func! CoompileAndRun()
	exec "call Coompile()"
	exec "call Run()"
endfunc 
