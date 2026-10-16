#pragma once
#include "Base.h"

// Администрация: ФИО, должность, область ответственности на конференции
class Administrator : public Base {
    std::string fullName, position, responsibility;
public:
    Administrator();
    Administrator(const std::string& fullName, const std::string& position,
                  const std::string& responsibility);
    Administrator(const Administrator& other);
    virtual ~Administrator();
    Administrator& operator=(const Administrator& other);
    bool operator==(const Administrator& other) const;

    const std::string& getFullName() const;
    const std::string& getPosition() const;
    const std::string& getResponsibility() const;
    void setFullName(const std::string& v);
    void setPosition(const std::string& v);
    void setResponsibility(const std::string& v);

    virtual void print(std::ostream& os) const;
    virtual void save(std::ostream& os) const;
    virtual void load(std::istream& is);
    virtual void edit();
    virtual Base* clone() const;
    virtual std::string typeName() const;
};
