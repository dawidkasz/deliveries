class Privelages{
    std::string description="";
    int priority=0;
    public:
    Privelages()=default;
    Privelages(std::string description, int priority=1):description(description), priority(priority){};
};