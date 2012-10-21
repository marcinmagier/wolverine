    #include <QCoreApplication>
    #include <QDebug>
     
    #include <Logger.h>
    #include <ConsoleAppender.h>
     
    int main(int argc, char* argv[])
    {
      QCoreApplication app(argc, argv);
      ...
      ConsoleAppender* consoleAppender = new ConsoleAppender();
      consoleAppender->setFormat("[%-7l] <%C> %m\n");
      Logger::registerAppender(consoleAppender);
      ...
      LOG_INFO("Starting the application");
      int result = app.exec();
      ...
      if (result)
        LOG_WARNING() << "Something went wrong." << "Result code is" << result;
     
      return result;
    }
