#!/bin/sh
printf "Welcome to the GAMECONSOLE!\n"
menu() {
  printf "Please choose your game.\n"
  printf "1.Tetris game\n"
  printf "2.terminal-mines\n"
  printf "3.arcade\n"
  printf "4.Exit\n"
  printf "Enter your choice: "
  read a
}
while true; do
  menu
  if [ "$a" -eq 1 ]; then
    if [ -x "./run/tinytetris" ]; then
      ./run/tinytetris
    else
      printf "Error: tinytetris is not compiled yet!\n"
    fi

  elif [ "$a" -eq 2 ]; then
    if [ -x "./run/terminal-mines-single" ]; then
      ./run/terminal-mines-single
    else
      printf "Error: terminal-mines-single is not compiled yet!\n"
    fi

  elif [ "$a" -eq 3 ]; then
    if [ -x "./run/ncurses-arcade" ]; then
      ./run/ncurses-arcade
    else
      printf "Error: ncurses-arcade is not compiled yet!\n"
    fi

  elif [ "$a" -eq 4 ]; then
    printf "\nGoodbye!\n\n"
    break

  else
    printf "Unknown choice, please try again!\n"
  fi

  sleep 1
  echo ""
done
