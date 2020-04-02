#!/usr/bin/env python3
import argparse
import subprocess
import os
from pathlib import Path

description = 'This is a command line utility to simplify building and running tests and examples of Beautifolds inside the provided docker container'

docker_container = 'corristo/clang:10.0.0'

docker_container_command = ['docker', 'run', '--rm', '-v', os.getcwd() + ':/source', '-v', os.getcwd() + '/build:/build', '-u', str(os.getuid()) + ':' + str(os.getgid())]

parser = argparse.ArgumentParser(description=description)
parser.add_argument("action", choices=['build', 'test', 'coverage', 'run-interactive'])
parser.add_argument("compiler", choices=['gcc', 'clang', 'msvc'], default='gcc', nargs='?')
args = parser.parse_args()

Path(os.path.join(os.getcwd(), 'build')).mkdir(parents=True, exist_ok=True)

if args.action == 'build':
    if args.compiler == 'gcc':
        docker_container_command.extend([docker_container, '/source/tools/scripts/linux/build-gcc.sh'])
        subprocess.run(docker_container_command)
    if args.compiler == 'clang':
        docker_container_command.extend([docker_container, '/source/tools/scripts/linux/build-clang.sh'])
        subprocess.run(docker_container_command)
    if args.compiler == 'msvc':
        print("Building with msvc is not supported at the moment.")
if args.action == 'test':
    if args.compiler == 'gcc':
        docker_container_command.extend([docker_container, '/source/tools/scripts/linux/test-gcc.sh'])
        subprocess.run(docker_container_command)
    if args.compiler == 'clang':
        docker_container_command.extend([docker_container, '/source/tools/scripts/linux/test-clang.sh'])
        subprocess.run(docker_container_command)
    if args.compiler == 'msvc':
        print("Running tests with msvc is not supported at the moment.")
if args.action == 'coverage':
    if args.compiler == 'gcc':
        docker_container_command.extend([docker_container, '/source/tools/scripts/linux/coverage.sh'])
        subprocess.run(docker_container_command)
    else:
        print("Coverage reporting is currently only supported with gcc")
if args.action == 'run-interactive':
        docker_container_command.extend(['-it', docker_container])
        subprocess.run(docker_container_command)
