# !/bin/bash

# Create docker image using the Dockerfile in the current directory
docker build -t icerage/mule .

# Push the docker image to DockerHub
docker push icerage/mule