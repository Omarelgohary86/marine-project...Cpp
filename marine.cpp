#include <iostream>
#include <cmath> 
#include <string> 

using namespace std;

//enter input and check if input value is invalid %
double check_value(string op_name) {
    double value;
    cout << "Enter " << op_name ;
    cin >> value;

    while (cin.fail() || value < 0 ) {
        cin.clear();                  //restart cin
        cin.ignore(1000, '\n');       //delete the wrong value
        cout << "Please enter a valid " << op_name ;
        cin >> value;       
    }
    return value;
}

int main() {
    cout<< R"(
|                                                           ~~  |  ~~                                                                    |
|                                                              / \                                                                       |
|                                                             /   \                                                                      |
|                                                            /  |  \                                                                     |
|                                                           /   |   \                                                                    |
|                                                          /    |    \                                                                   |
|                                                         /     |     \                                                                  |
|                                           ____________ /______|______\ ____________                                                    |
|                                           \                                       /                                                    |
|                                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                 |
|                                            \_____________________________________/                                                     |
|                                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                      |
__________________________________________________________________________________________________________________________________________                         
    )"<<endl;

    //1. input variables
    double wave_safe , wind_safe , vis_safe ;
    int n;

    cout<<"=== Enter Reference Limits ===" << endl;
    //2.1 wave safe/danger limit
    cout<<"-------> WAVE"<<endl;
    wave_safe =  check_value("Wave Safe/Danger Height (m) :"  );

    //2.2 wind safe/danger limit
    cout<<"-------> Wind"<<endl;
    wind_safe =  check_value("Wind Safe/Danger Speed (km/h) :");

    //2.3 visibility safe/danger limit
    cout<<"-------> Visibility"<<endl;
    vis_safe  =  check_value("Visibility Safe/Danger (km) : " );
    
    //3. n number of observation
    cout<<"-------> n"<<endl;
    cout << "Enter Number of Observations (n) : ";
    cin >> n;
    //check if n is not a valid value
    while ( n <= 0 || cin.fail() ){
        cin.clear();                      //restart cin
        cin.ignore(1000 , '\n');         //delete the wrong value
        cout << "Invalid number! Enter a positive number for observations: ";
        cin >> n; }
    cout << "\n___________________________________________________________________________________________________________________________________________" << endl;

    //4. three values for each observation
    double    open_count = 0,       caution_count = 0,    closed_count = 0          ;
    string wave_safe_or_danger , wind_safe_or_danger , visibility_safe_or_danger ;
    double wave_sum = 0, wind_sum = 0, vis_sum = 0;
    double max_wave  = 0  ;
    double max_wind  = 0  ;
    double min_vis   = 99999999999  ; 
    int    worst_status_no  ;
    
    //5. loop for each observation
    for (int i = 1; i <= n; i++) {
        
        cout << "\n------------- Observation #" << i << " -------------" << endl;

        double obs_wave, obs_wind, obs_vis;
        obs_wave =  check_value("Wave Height (m) :"  );
        obs_wind =  check_value("Wind Speed (km/h) :");
        obs_vis  =  check_value("Visibility (km) :"  );

        // sums
        wave_sum +=  obs_wave ;
        wind_sum +=  obs_wind ;
        vis_sum  +=  obs_vis  ;

        //determine max/min value
        if (obs_wave > max_wave)  {max_wave = obs_wave;}
        if (obs_wind > max_wind)  {max_wind = obs_wind;}
        if (obs_vis  <  min_vis)  {min_vis  =  obs_vis;}
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Port status------> ";

        // wave checking
        if        (obs_wave >= wave_safe)   {wave_safe_or_danger = "danger"      ;} 
        else if   (obs_wave < wave_safe )   {wave_safe_or_danger = "safe"        ;}
        // wind checking
        if        (obs_wind >= wind_safe)   {wind_safe_or_danger = "danger"      ;} 
        else if   (obs_wind < wind_safe )   {wind_safe_or_danger = "safe"        ;}
        // visibility checking
        if        (obs_vis  <=  vis_safe)   {visibility_safe_or_danger = "danger";} 
        else if   (obs_vis  >  vis_safe )   {visibility_safe_or_danger = "safe"  ;}

        // port status > Open|Caution|Closed
        string port_status ;
        if (wave_safe_or_danger == "safe" && wind_safe_or_danger=="safe" && visibility_safe_or_danger=="safe")
            {open_count++;   port_status= "OPEN"; cout<<port_status<<endl; worst_status_no=0;}

        else if (wave_safe_or_danger == "safe" && wind_safe_or_danger=="safe" && visibility_safe_or_danger=="danger") 
            {caution_count++;  port_status= "CAUTION"; cout<<port_status<<"   | Low visibility"<<endl ;worst_status_no=1;} 

        else if (wave_safe_or_danger == "safe" && wind_safe_or_danger=="danger" && visibility_safe_or_danger=="safe") 
            {caution_count++;  port_status= "CAUTION"; cout<<port_status<<"   | The Winds are dangerous"<<endl;worst_status_no=2;} 

        else if (wave_safe_or_danger == "danger" && wind_safe_or_danger=="safe" && visibility_safe_or_danger=="safe") 
            {caution_count++;  port_status= "CAUTION"; cout<<port_status<<"   | The Waves are dangerous"<<endl;worst_status_no=3;} 

        else if (wave_safe_or_danger == "danger" && wind_safe_or_danger=="danger" && visibility_safe_or_danger=="danger")
            {closed_count++;   port_status= "CLOSED"; cout<<port_status<<"   | The Winds are dangerous | The Waves are dangerous | Low visibility"<<endl;
            worst_status_no=4;}

        else if (wave_safe_or_danger == "danger" && wind_safe_or_danger=="danger" && visibility_safe_or_danger=="safe")
            {closed_count++;   port_status= "CLOSED"; cout<<port_status<<"   | The Winds are dangerous | The Waves are dangerous"<<endl;worst_status_no=5;}

        else if (wave_safe_or_danger == "danger" && wind_safe_or_danger=="safe" && visibility_safe_or_danger=="danger")
            {closed_count++;   port_status= "CLOSED"; cout<<port_status<<"   | The Waves are dangerous | Low visibility"<<endl;worst_status_no=6;}

        else if (wave_safe_or_danger == "safe" && wind_safe_or_danger=="danger" && visibility_safe_or_danger=="danger")
            {closed_count++;   port_status= "CLOSED"; cout<<port_status<<"   | The Winds are dangerous | Low visibility"<<endl;worst_status_no=7;}
    }

    cout << "___________________________________________________________________________________________________________________________________________" << endl;
    //6. calculations
    double open_percent = (open_count / n) * 100;
    double caution_percent = (caution_count / n) * 100;
    double closed_percent = (closed_count / n) * 100;

    cout << "\n================================================" << endl;
    cout << "              FINAL SUMMARY REPORT           " << endl;
    cout << "================================================" << endl;

    cout << "Port Status Percentages:" << endl;
    cout << " - OPEN     :  " <<open_percent << " % (" << open_count << " times)" << endl;
    cout << " - CAUTION  :  " <<caution_percent << " % (" << caution_count << " times)" << endl;
    cout << " - CLOSED   :  " <<closed_percent << " % (" << closed_count << " times)" << endl;

    cout << "\nAverages Across All Observations:" << endl;
    cout << " - Average Wave Height   :  " << (wave_sum / n) << " m" << endl;
    cout << " - Average Wind Speed    :  " << (wind_sum / n) << " km/h" << endl;
    cout << " - Average Visibility    :  " << (vis_sum / n) << " km" << endl;

    cout << "\nExtremes Recorded:" << endl;
    cout << " - Maximum Wave Height  :  " << max_wave << " m" << endl;
    cout << " - Maximum Wind Speed   :  " << max_wind << " km/h" << endl;
    cout << " - Minimum Visibility   :  " << min_vis << " km" << endl;

    cout << "\nFinal Overall Worst Status: ";
    if (worst_status_no == 0) {cout << "OPEN -------> no worst status" << endl; }
    else if (worst_status_no == 1) cout << "CAUTION  | Low visibility" << endl;
    else if (worst_status_no == 2) cout << "CAUTION  | The Winds are dangerous" << endl;
    else if (worst_status_no == 3) cout << "CAUTION  | The Waves are dangerous" << endl;
    else if (worst_status_no == 4) cout << "CLOSED   | The Winds are dangerous | The Waves are dangerous | Low visibility" << endl;
    else if (worst_status_no == 5) cout << "CLOSED   | The Winds are dangerous | The Waves are dangerous" << endl;
    else if (worst_status_no == 6) cout << "CLOSED   | The Waves are dangerous | Low visibility" << endl;
    else if (worst_status_no == 7) cout << "CLOSED   | The Winds are dangerous | Low visibility" << endl;
    

    // 7. BONUS: Harbor Dashboard Visualization
    cout << "\n==============================================" << endl;
    cout << "             BONUS: HARBOR DASHBOARD           " << endl;
    cout << "================================================" << endl;
    
    cout << "OPEN    [" << open_percent << "%] : ";
    for (int i = 0; i < (int)(open_percent / 5); i++) cout << "#";
    cout << endl;

    cout << "CAUTION [" << caution_percent << "%] : ";
    for (int i = 0; i < (int)(caution_percent / 5); i++) cout << "#";
    cout << endl;

    cout << "CLOSED  [" << closed_percent << "%] : ";
    for (int i = 0; i < (int)(closed_percent / 5); i++) cout << "#";
    cout << endl;

    cout << "================================================" << endl;

    return 0;
}