LibTwitter-Core
===============

**LibTwitter C++** (or LibTwitter Cpp or LibTwitter) is a C++ Twitter API library.

**LibTwitter** will be divided in two layers :


* **LibTwitter-Core** - _(Status : In development)_
Using libcURL, **LibTwitter-Core** provides features to easily send requests (REST 1.1 or Streaming) to Twitter API and retrieve raw JSON responses.

* **LibTwitter(-Easy)** _(Status : Not started yet)_
This layer will use _**LibTwitter-Core**_ and a JSON parser, in order to provide higher level methods, allowing programmers to manipulate C++ Ojects (Tweet, User, Timeline, etc ...) and methods ( Tweet::retweet(...), Tweet::reply(...), User::send_message(...), etc )
