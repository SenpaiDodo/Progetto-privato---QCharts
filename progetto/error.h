#ifndef ERROR_H
#define ERROR_H
#include <QString>

class ErrorAdd{};
class Max{};
class ErrorInput{};
class Zero{};
class ErrorOpen{
    QString error;
 public:
    ErrorOpen(QString e):error(e){}
    QString Error() const{return error;}
};
class ErrorSave{};
class OnlyRead{};
class EmptyData{
private:
    bool closeempty;
public:
    EmptyData(bool c=false):closeempty(c){}
    bool GetCloseEmpty() const
    {
        return closeempty;
    }
};

#endif // ERROR_H
