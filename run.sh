#!/bin/bash
set -x
sudo nginx -c $PWD/nginx.conf
spawn-fcgi -p 8000 -n csit314
