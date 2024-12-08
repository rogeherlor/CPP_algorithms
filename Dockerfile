# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set non-interactive mode to prevent prompts during installation
ARG DEBIAN_FRONTEND=noninteractive

# Update, install common packages, and clean up in a single layer
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    gcc \
    g++ \
    gdb \
    gdbserver \
    curl \
    vim \
    git \
    nano \
    net-tools \
    python3 \
    python3-pip \
    python3-dev \
    build-essential \
    unzip \
    wget \
    lsb-release \
    ca-certificates \
    libcurl4-openssl-dev \
    libboost-all-dev

# Install common Python packages
RUN pip3 install --no-cache-dir \
    numpy==1.23.5 \
    pandas==1.5.3 \
    matplotlib==3.6.2 \
    requests==2.28.2 \
    flask==2.2.2 \
    scipy==1.9.3 \
    jupyter==1.0.0

# Set environment variables
ENV PYTHONUNBUFFERED=1 \
    LANG=C.UTF-8 \
    LC_ALL=C.UTF-8

# Set default working directory
WORKDIR /app