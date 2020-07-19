#ifndef HEALTHMODEL_HPP
#define HEALTHMODEL_HPP

enum Health_Status
{
    Health_Status_No_More  = 0,
    Health_Status_Still_Is = 1
};

class HealthModel
{
public:
    HealthModel();
    ~HealthModel();
    int getCurrentHealthInPercent() const;
    void add(int healthPoints);
    Health_Status subtract(int healthPoints);

protected:
    int m_currentHealth;
};

#endif // HEALTHMODEL_HPP
