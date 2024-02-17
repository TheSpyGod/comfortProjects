#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <ctype.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
// ANSI escape code to reset text color
#define ANSI_COLOR_RESET   "\x1b[0m"

void fetchJson() {
  
  // You can implement this function to fetch JSON data
   FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;

    fp = fopen("info.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    // Iterate over each category
    json_object_object_foreach(parsed_json, key, val) {
        printf("\n\t\t%s:\n\n", key);

        // Assuming each category contains an array of objects
        json_object *category_array = val;
        for (int i = 0; i < json_object_array_length(category_array); i++) {
            // Iterate over each subject within the category
            json_object *category_obj = json_object_array_get_idx(category_array, i);
            json_object_object_foreach(category_obj, sub_key, sub_val) {
               printf("%s: ", sub_key);
                // Print the number with green color
                printf(ANSI_COLOR_GREEN "\t%d  " ANSI_COLOR_RESET, json_object_get_int(sub_val));
            }
        }
     printf("\n");
    }
}

void interface(char status) {
  switch (status) {
      case 'r':
        fetchJson();
      //case 'u':
        //updateJson();
  }
}

int main() {
 char status;
  while (status != 'q' && status != 'Q') {
  status = ' ';
  printf("Update or Review studies? R - review, U - Update\n");
  scanf("%c", &status);
  interface(status);
  getchar();
  };
    return 0;
}
