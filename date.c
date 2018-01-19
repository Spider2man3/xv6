#include "types.h"
#include "user.h"
#include "date.h"

// An array for the names of the months
static char* monthnames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int
main(int argc, char *argv[])
{
  struct rtcdate r;

  if (date(&r)) {
    printf(2, "date failed\n");
    exit();
  }

  // Print the date and time
  printf(1, "%s %d, %d %d:%d:%d\n", monthnames[r.month - 1], r.day, r.year, r.hour, r.minute, r.second);
  exit();
}