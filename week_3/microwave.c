#include <stdio.h>

#define TEN_MINS 600
#define ONE_MIN  60
#define TEN_SECS 10

int get_time(void);
int button_calc(int buttons[], int time_required);

int main(void)
{
    /* Three buttons - 10mins, 1min, 10secs */
    /* Make array to store cooking buttons */
    int buttons[3] = {TEN_MINS, ONE_MIN, TEN_SECS};
    int time_required, min_button_presses;
    time_required = get_time();
    min_button_presses = button_calc(buttons, time_required);
    printf("Number of button presses = %d\n", 
    min_button_presses);
    return 0;
}

int get_time(void)
{
    int time;
    printf("Type the time required\n");
    scanf("%d", &time);
    return time;
}

int button_calc(int buttons[], int time_required)
{
    int i, count = 0;
    for(i=0; i<3; i++){
        while(time_required / buttons[i] >= 1){
            time_required -= buttons[i];
            count++;
        }
    }
    if(time_required < TEN_SECS && time_required > 0){
        count++;
    }
    return count;
}