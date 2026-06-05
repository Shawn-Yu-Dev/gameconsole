import subprocess
import os
import sys


def menu():
    print("Welcome to the GAMECONSOLE!")
    print("Please choose your game.")
    print("1.Tetris game")
    print("2.Tetrisrminal mines")
    print("3.arcade")
    print("4.nsnake")
    print("5.Exit(q)")


gamemapping = {
    "1": "./run/tinytetris",
    "2": "./run/terminal-mines-single",
    "3": "./run/ncurses-arcade",
    "4": "./run/nsnake",
}

while True:
    os.system("clear")
    menu()
    menuselection = input("Enter your choice:  ").strip()
    if menuselection == "q":
        print("Goodbye!")
        sys.exit(0)
    if menuselection in gamemapping:
        binarypath = gamemapping[menuselection]
        if os.path.isfile(binarypath) and os.access(binarypath, os.X_OK):
            subprocess.run([binarypath])
        else:
            print(f"Error: {binarypath} 未编译或没有执行权限！")
    else:
        print("Unknown choice, please try again!")
        input("按回车键继续...")
