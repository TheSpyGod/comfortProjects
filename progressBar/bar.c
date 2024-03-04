#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <json-c/json.h>

void dbconn(const char *db_host, const char *db_user, const char *db_password, const char *db_name) {
    MYSQL *conn = mysql_init(NULL);
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (conn == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(2);
    }

    if (mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(2);
    }

    if (mysql_query(conn, "SELECT IFNULL(pochodne, 'null'), IFNULL(calki, 'null'), IFNULL(macierze, 'null'), IFNULL(p_projekty, 'null'), IFNULL(p_jezyki, 'null'), IFNULL(p_czas, 'null'), IFNULL(a_projekty, 'null'), IFNULL(a_kursy, 'null'), IFNULL(a_czas, 'null'), IFNULL(szeregi, 'null') FROM progress")) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(2);
    }

    res = mysql_use_result(conn);

    // Print header row
    printf("+----------+-------+----------+------------+----------+--------+------------+---------+--------+---------+\n");
    printf("| pochodne | calki | macierze | p_projekty | p_jezyki | p_czas | a_projekty | a_kursy | a_czas | szeregi |\n");
    printf("+----------+-------+----------+------------+----------+--------+------------+---------+--------+---------+\n");

    // Print data rows
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("| %-7s | %-5s | %-8s | %-10s | %-8s | %-6s | %-10s | %-7s | %-6s | %-7s |\n",
               row[1], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9]);
    }

    // Print bottom border
    printf("+----------+-------+----------+------------+----------+--------+------------+---------+--------+---------+\n");

    mysql_free_result(res);
    mysql_close(conn);
}

void readConfig() {
    FILE *fp = fopen("config.json", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open configuration file.\n");
        exit(2);
    }

    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    json_object *config = json_tokener_parse(buffer);
    if (config == NULL) {
        fprintf(stderr, "Error: Invalid configuration format.\n");
        exit(2);
    }

    const char *db_host = json_object_get_string(json_object_object_get(config, "db_host"));
    const char *db_user = json_object_get_string(json_object_object_get(config, "db_user"));
    const char *db_password = json_object_get_string(json_object_object_get(config, "db_password"));
    const char *db_name = json_object_get_string(json_object_object_get(config, "db_name"));

    dbconn(db_host, db_user, db_password, db_name);
}

void interface(char status) {
    switch (status) {
        case 'r':
        case 'R':
            readConfig();
            break;
        default:
            break;
    }
}

int main() {
    printf("\nUpdate or Review studies? R - review, U - Update\n");
    char status;
    while (status != 'q' && status != 'Q') {
        status = ' ';
         scanf(" %c", &status);
        interface(status);
        getchar();
    };
    return 0;
}
