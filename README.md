# Project: rowingclub

## Set the database in directory db:

```diff
! sqlite3 viena.db < init.sql
```

## Set environment variable for the absolute path of the database file:

```diff
+ Linux based systems terminal:
- export MYDB=<absolute_path>

+ Qt Creator:
- Edit > Preferences > Environment > System (tab) and change the Environment by adding MYDB=<absolute_path> line
```

## Compile

```diff
! qmake && make
```

## Run

```diff
! ./viena
```
