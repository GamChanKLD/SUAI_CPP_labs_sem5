#pragma once
#include "Base.h"

// Программа конференции: день, время выступления, наименование
class ProgramItem : public Base {
    int day;
    std::string time;   // формат ЧЧ:ММ
    std::string title;
public:
    ProgramItem();
    ProgramItem(int day, const std::string& time, const std::string& title);
    ProgramItem(const ProgramItem& other);
    virtual ~ProgramItem();
    ProgramItem& operator=(const ProgramItem& other);
    bool operator==(const ProgramItem& other) const;
    bool operator<(const ProgramItem& other) const;   // по дню и времени

    int getDay() const;
    const std::string& getTime() const;
    const std::string& getTitle() const;
    void setDay(int v);
    void setTime(const std::string& v);
    void setTitle(const std::string& v);

    virtual void print(std::ostream& os) const;
    virtual void save(std::ostream& os) const;
    virtual void load(std::istream& is);
    virtual void edit();
    virtual Base* clone() const;
    virtual std::string typeName() const;
};
