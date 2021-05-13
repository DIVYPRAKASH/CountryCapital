#!/bin/bash

exec docker run -it  --net=host server:latest ./country_server
