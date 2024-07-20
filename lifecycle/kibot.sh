#!/bin/sh

# Determine the directory of the script
SCRIPT_DIR="$(dirname "$0")"

# Construct the paths to the .env and .env.sample files
ENV_FILE="$SCRIPT_DIR/.env"
ENV_SAMPLE_FILE="$SCRIPT_DIR/.env.sample"

if [ ! -f "$ENV_FILE" ]; then
  if [ -f "$ENV_SAMPLE_FILE" ]; then
    cp "$ENV_SAMPLE_FILE" "$ENV_FILE"
  else
    echo ".env file not found and .env.sample does not exist"
    exit 1
  fi
fi

# Load .env file
if [ -f "$ENV_FILE" ]; then
  source "$ENV_FILE"
else
  echo ".env file not found at $ENV_FILE"
  exit 1
fi


export USER_ID=$(id -u)
export GROUP_ID=$(id -g)
export WORKDIR=$(pwd)
export SUBDIR=electronics
export OUTPUTDIR=$WORKDIR/deliverables

echo $LOCAL_KICADCONFIG
mkdir -p $OUTPUTDIR

docker run --rm -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY \
    -v $WORKDIR:/home/$USER/workdir \
    --user $USER_ID:$GROUP_ID \
    --workdir="/home/$USER/" \
    --volume="$LOCAL_KICADCONFIG:/home/$USER/.config/kicad:rw" \
    --volume="$HOME/.local/share:/home/$USER/.local/share:rw" \
    --volume="$HOME/.cache:/.cache:rw" \
    --env XDG_DATA_HOME=/home/$USER/.local/share \
    --env KICAD_CONFIG_HOME=/home/$USER/.config/kicad \
    --env USERMODELS=/home/$USER/.config/kicad/7.0 \
    --env KICAD8_3DMODEL_DIR=/kicad/3dmodels \
    ghcr.io/inti-cmnb/kicad8_auto:latest /bin/bash -c " cd workdir/$SUBDIR ; kibot -c ../lifecycle/config-kibot.yaml -d ../deliverables"