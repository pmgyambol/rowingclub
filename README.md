# Project: rowingclub

## Set the database in directory db:

sqlite3 viena.db < init.sql

## Set environment variable for the absolute path of the database file:

```diff
+ Linux based systems
- export MYDB=<absolute_path>

+ Qt Creator
Edit > Preferences > Environment > System (tab) and change the Environment by adding MYDB=<absolute_path> line
```

## Compile

qmake && make

## Run

./viena

