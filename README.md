# Project: rowingclub

## Set the database in directory db:

sqlite3 viena.db < init.sql

## Set environment variable for the absolute path of the database file:

export MYDB=<absolute_path>  - Linux based systems

Edit > Preferences > Environment > System (tab) and change the Environment by adding MYDB=<absolute_path> line - Qt Creator

## Compile

qmake && make

## Run

./viena

