#!/usr/bin/env bash

SCRIPT_NAME=$(basename "$0")
readonly SCRIPT_NAME

TARGET_FOLDER="$1"
readonly TARGET_FOLDER

SCRIPT_FOLDER=$( cd "$( dirname "$0" )" && pwd )
readonly SCRIPT_FOLDER

PROJECT_ROOT=$(dirname "${SCRIPT_FOLDER}")
readonly PROJECT_ROOT

EXECUTABLE_PATH="${PROJECT_ROOT}/bin/download_organizer"
readonly EXECUTABLE_PATH

# Exit on error
# Prevent errors on pipeline from being masked
set -eo pipefail;

function main()
{
    ensure_target_folder_was_passed "${TARGET_FOLDER}"
}

function ensure_target_folder_was_passed()
{
    local target_folder="$1"

    if [ -z "${target_folder}" ]
    then
        display_usage

        exit 1
    fi
}

function display_usage()
{
    echo -e "\n"
    echo -e "Usage:"
    echo -e "    ${SCRIPT_NAME} TARGET_FOLDER\n"
    echo -e "Example:"
    echo -e "    ${SCRIPT_NAME} /home/some_user/Downloads"
    echo -e "\n"
}

main "$@"
