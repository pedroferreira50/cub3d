FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    git \
    libx11-dev \
    libxext-dev \
    libgl1-mesa-dev \
    libglfw3-dev \
    libbsd-dev \
    valgrind \
    x11-utils

# Set work directory
WORKDIR /app
