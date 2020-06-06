#!/bin/bash

readonly PROJECT_ROOT=$( cd "$( dirname "$0" )" && pwd )

readonly C_CPP_EXTENSIONS_REGEX='[.](c|cc|cp|cxx|cpp|CPP|c[+]{2}|C|h|hpp)$'

readonly MODE="$1"

function main()
{
  ensure_mode_is_valid "$MODE"
  ensure_main_file_exists "src"

  if [ "$MODE" = "--test" ]
  then
    ensure_main_file_exists "tests"
  fi

  while true; do
    case "$MODE" in
      --run)
        find "$PROJECT_ROOT/bin" -type f |
        entr -d bash entr_script.sh "$PROJECT_ROOT" "$MODE"
        ;;
      *)
        find "$PROJECT_ROOT" -type f |
        grep -E "$C_CPP_EXTENSIONS_REGEX" |
        entr -d bash entr_script.sh "$PROJECT_ROOT" "$MODE"
    esac

  done
}

function ensure_mode_is_valid()
{
  case "$1" in
    --run)
      ;;
    --test)
      ;;
    --compile)
      ;;
    *)
      echo 'ERROR'
      print_usage
      exit 1
  esac
}

function ensure_main_file_exists()
{
  local main_file=''

  while true; do
    main_file=$(find "$PROJECT_ROOT/$1" -type f | grep -E "/main$C_CPP_EXTENSIONS_REGEX")

    if [ -z "$main_file" ]
    then
      echo -e "\nERROR"
      echo "No main file found on '$1' folder!"
      echo "Please name your main file as 'main' with the appropriate extension."
      echo -e "\nRetrying in 5 seconds..."
      sleep 5
    else
      break
    fi
  done
}

function print_usage()
{
  echo 'Usage: '
  echo "   $0 [--run|--test|--compile]"
}

main "$@"
