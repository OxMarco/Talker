#ifndef FILEIO_H
#define FILEIO_H

String readFile(fs::FS &fs, const char * path){
    String stream = "";

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return "";
    }

    while(file.available()){
        stream += (char)(file.read());
    }

    return stream;
}

bool writeFile(fs::FS &fs, const char * path, const char * message){
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return false;
    }
    if(file.print(message)){
      return true;
    } else {
      return false;
    }
}

bool appendFile(fs::FS &fs, const char * path, const char * message){
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return false;
    }
    if(file.print(message)){
        return false;
    } else {
        return true;
    }
}

#endif // FILEIO_H
