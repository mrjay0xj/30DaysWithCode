#include <iostream>

#define LOG(x) {std::cout << x;}
#define GET(x) {std::cin >> x;}
#define LOG_GET(x,y) {std::cout << x;std::cin >> y;}

#define PRICE_BASE 10000

typedef double unit_base;
typedef double carry_value;

struct answer_result
{
    carry_value Metric_value;
    carry_value Final_price;
    carry_value Sqaure_meter_needed_ceramics;
    carry_value Count_of_needed_ceramics;

    answer_result() :
        Metric_value(0),  Final_price(0),  Sqaure_meter_needed_ceramics(0),  Count_of_needed_ceramics(0) {}

    answer_result(unit_base metric_value, unit_base final_price, unit_base sqaure_meter_needed_ceramics, unit_base count_of_needed_ceramics) :
        Metric_value(metric_value),  Final_price(final_price),  Sqaure_meter_needed_ceramics(sqaure_meter_needed_ceramics),
        Count_of_needed_ceramics(count_of_needed_ceramics) {}

    friend std::ostream& operator <<(std::ostream& os, answer_result answr_res)
    {
        os << "Metric Size: " << answr_res.Metric_value << "\nFinal Price: " << answr_res.Final_price <<
            "\nSquare meter of all price needed: " << answr_res.Sqaure_meter_needed_ceramics << "\nCount of needed ceramics: "
            << answr_res.Count_of_needed_ceramics << "\n";
        return os;
    }
};

class Calculate_Program
{
private:
    unit_base width;
    unit_base length;
    unit_base unit_price;
    unit_base size_per_cm;
    unit_base size_per_m;

    carry_value pices_fit_width;
    carry_value total_number;
    carry_value total_area;
    carry_value total_cost;
    carry_value cost_per_one_strip;
    carry_value additional_cost;
    carry_value total_cost_meter;
    carry_value length_of_material_used;
    carry_value ratio_of_usedarea_to_total_area;
public:
    void Get_Inputs()
    {
        LOG_GET("Enter the width: ", width);
        LOG_GET("Enter the length: ", length);
        LOG_GET("Enter the unit price: ", unit_price);
        LOG_GET("Enter the size per cm: ", size_per_cm);
        LOG_GET("Enter the size per m: ", size_per_m);
    }
    answer_result calculate_values()
    {
        pices_fit_width = width * size_per_cm;

        total_number = length * pices_fit_width;

        total_area = length * width;

        total_cost = total_area * unit_price;

        cost_per_one_strip = total_cost / total_number;

        additional_cost = cost_per_one_strip + PRICE_BASE;

        total_cost_meter = additional_cost * size_per_m;

        length_of_material_used = size_per_cm * size_per_m;

        ratio_of_usedarea_to_total_area = length_of_material_used / total_area;

        return answer_result(additional_cost, total_cost_meter, length_of_material_used, ratio_of_usedarea_to_total_area);
    }
};

int main()
{
    Calculate_Program calc_app;

    calc_app.Get_Inputs();
    LOG(calc_app.calculate_values());

    return 0;
}
