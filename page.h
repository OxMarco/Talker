#ifndef PAGE_H
#define PAGE_H

const char PAGE_HEADER[] = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Communicator</title>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width,
initial-scale=0.75, maximum-scale=0.75, user-scalable=no'>
<style>
body {
  padding: 0;
  margin: 0;
  background: -moz-linear-gradient(-45deg, #183850 0, #183850 25%, #192C46 50%, #22254C 75%, #22254C 100%);
  background: -webkit-linear-gradient(-45deg, #183850 0, #183850 25%, #192C46 50%, #22254C 75%, #22254C 100%);
  background-repeat: no-repeat;
  background-attachment: fixed;
}

::-webkit-scrollbar {
  width: 10px;
}

::-webkit-scrollbar-track {
  border-radius: 10px;
  background-color: rgba(25, 147, 147, 0.1);
}

::-webkit-scrollbar-thumb {
  border-radius: 10px;
  background-color: rgba(25, 147, 147, 0.2);
}

.chat-thread {
  margin: 24px auto 0 auto;
  padding: 0 20px 0 0;
  list-style: none;
  overflow-y: scroll;
  overflow-x: hidden;
}

.chat-thread li {
  position: relative;
  clear: both;
  display: inline-block;
  padding: 16px 40px 16px 20px;
  margin: 0 0 20px 0;
  font: 16px/20px sans-serif;
  border-radius: 10px;
  background-color: rgba(25, 147, 147, 0.2);
}

/* Chat - Avatar */
.chat-thread li:before {
  position: absolute;
  top: 0;
  width: 50px;
  height: 50px;
  border-radius: 50px;
  content: '';
}

/* Chat - Speech Bubble Arrow */
.chat-thread li:after {
  position: absolute;
  top: 15px;
  content: '';
  width: 0;
  height: 0;
  border-top: 15px solid rgba(25, 147, 147, 0.2);
}

.me {
  animation: show-chat-odd 0.15s 1 ease-in;
  -moz-animation: show-chat-odd 0.15s 1 ease-in;
  -webkit-animation: show-chat-odd 0.15s 1 ease-in;
  float: right;
  margin-right: 80px;
  color: #0AD5C1;
}

.me:after {
  border-right: 15px solid transparent;
  right: -15px;
}

.you {
  animation: show-chat-even 0.15s 1 ease-in;
  -moz-animation: show-chat-even 0.15s 1 ease-in;
  -webkit-animation: show-chat-even 0.15s 1 ease-in;
  float: left;
  margin-left: 80px;
  color: #0EC879;
}

.you:after {
  border-left: 15px solid transparent;
  left: -15px;
}

.chat-window {
  position: fixed;
  bottom: 18px;
}

.chat-window-message {
  width: 100%;
  height: 48px;
  font: 32px/48px sans-serif;
  background: none;
  color: #0AD5C1;
  border: 0;
  border-bottom: 1px solid rgba(25, 147, 147, 2);
  outline: none;
}

/* Small screens */
@media all and (max-width: 767px) {
  .chat-thread {
    width: 90%;
    height: 260px;
  }

  .chat-window {
    left: 5%;
    width: 90%;
  }
}
/* Medium and large screens */
@media all and (min-width: 768px) {
  .chat-thread {
    width: 50%;
    height: 320px;
  }

  .chat-window {
    left: 25%;
    width: 50%;
  }
}
@keyframes show-chat-even {
  0% {
    margin-left: -480px;
  }
  100% {
    margin-left: 0;
  }
}
@-moz-keyframes show-chat-even {
  0% {
    margin-left: -480px;
  }
  100% {
    margin-left: 0;
  }
}
@-webkit-keyframes show-chat-even {
  0% {
    margin-left: -480px;
  }
  100% {
    margin-left: 0;
  }
}
@keyframes show-chat-odd {
  0% {
    margin-right: -480px;
  }
  100% {
    margin-right: 0;
  }
}
@-moz-keyframes show-chat-odd {
  0% {
    margin-right: -480px;
  }
  100% {
    margin-right: 0;
  }
}
@-webkit-keyframes show-chat-odd {
  0% {
    margin-right: -480px;
  }
  100% {
    margin-right: 0;
  }
}
</style>
</head>
<body>
<ul class='chat-thread'>
)=====";

const char PAGE_FOOTER[] = R"=====(
</ul>

<form class='chat-window' action='/send' method='POST'>
    <input class='chat-window-message' name='msg' type='text' spellcheck='on' autocomplete='on' minlength='2' maxlength='250' autofocus required />
</form>
</body>
</html>
)=====";

#endif // PAGE_H
