# ChitChat - virtual space to hangout with friends and play simple arcades

### Decriprion:

ChitChat is a QT-based C++ application, that allows people to visit virtual rooms, talk with friends via voice chat and play videogames, such as Arkanoid, Hangman, etc. It is a semester project made by first-year bachelors of HSE SPb AMI.

### Building and using:

ChitChat comes with three major parts, that have to be built and used separately: server-side application, client-side application and games in form of shared libraries.

* **Server:** `cmake --build $DIR --target=ChitChatServer`, compile with `-DLOCAL` flag to run server on localhost. 
* **Client:** `cmake --build $DIR --target=ChitChatClient`, compile with `-DLOCAL` flag to connect to server on localhost.
* **Games:** `cmake --build $DIR -- target="name"`.

### Dependencies:

##### Server:

* `postgresql` 15 - PostgreSQL database.
* `libpqxx` 7.1.1 - official C++ PostgreSQL library.
* `Qt` 5 with modules `Widgets` and `Network` - GUI and network.

##### Client:

* `Qt` 5 with modules 'Widgets' and 'Network' - GUI and network.
* `Arkanoid` shared library.
* `Hangman` shared library.

##### Games:

* `Qt` 5 with modules `Widgets` and `Network` - GUI and network.
