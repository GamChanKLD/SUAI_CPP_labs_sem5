#pragma once
#include "Base.h"

// Выступающий: ФИО, организация/ВУЗ, доклад, аннотация доклада
class Speaker : public Base {
    std::string fullName, organization, topic, annotation;
public:
    Speaker();
    Speaker(const std::string& fullName, const std::string& organization,
            const std::string& topic, const std::string& annotation);
    Speaker(const Speaker& other);
    virtual ~Speaker();
    Speaker& operator=(const Speaker& other);
    bool operator==(const Speaker& other) const;

    const std::string& getFullName() const;
    const std::string& getOrganization() const;
    const std::string& getTopic() const;
    const std::string& getAnnotation() const;
    void setFullName(const std::string& v);
    void setOrganization(const std::string& v);
    void setTopic(const std::string& v);
    void setAnnotation(const std::string& v);

    virtual void print(std::ostream& os) const;
    virtual void save(std::ostream& os) const;
    virtual void load(std::istream& is);
    virtual void edit();
    virtual Base* clone() const;
    virtual std::string typeName() const;
};
