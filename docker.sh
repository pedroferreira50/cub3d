#!/bin/sh

docker run -it \
    --env DISPLAY=host.docker.internal:0 \
    --volume /tmp/.X11-unix:/tmp/.X11-unix \
    --volume .:/app \
    cub3d-linux