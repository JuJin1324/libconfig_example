#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <string.h>

/*
 * key = value
 * name = jujin
 * age = 29
 * country = Korea
 * status = hungry
 */
int main() {
    config_t config;
    config_setting_t *root, *setting;

    char key[16];
    const char *string_value;
    int int_value;

    const char file_path[] = "../example.cfg";

    /* config_t 변수 초기화 */
    config_init(&config);

    /* Read the file. If there is an error, report it and exit. */
    if (!config_read_file(&config, file_path)) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&config),
                config_error_line(&config), config_error_text(&config));
        config_destroy(&config);
        return (EXIT_FAILURE);
    }

    /* Get the store name. */
    strcpy(key, "name");
    if (!config_lookup_string(&config, key, &string_value))
        fprintf(stderr, "No '%s' key in configuration file.\n", key);
    printf("%s : %s\n", key, string_value);

    strcpy(key, "country");
    if (!config_lookup_string(&config, key, &string_value))
        fprintf(stderr, "No '%s' key in configuration file.\n", key);
    printf("%s : %s\n", key, string_value);

    strcpy(key, "status");
    if (!config_lookup_string(&config, key, &string_value))
        fprintf(stderr, "No '%s' key in configuration file.\n", key);
    printf("%s : %s\n", key, string_value);

    strcpy(key, "age");
    if (!config_lookup_int(&config, key, &int_value))
        fprintf(stderr, "No '%s' key in configuration file.\n", key);
    printf("%s : %d\n", key, int_value);

    root = config_root_setting(&config);
    strcpy(key, "age");
    setting = config_setting_get_member(root, key);
    config_setting_set_int(setting, 100);

    /* Write out the updated configuration. */
    if (!config_write_file(&config, file_path)) {
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(&config);
        return (EXIT_FAILURE);
    }
    printf("Updated configuration successfully written to: %s\n", file_path);

    if (!config_lookup_int(&config, key, &int_value))
        fprintf(stderr, "No '%s' key in configuration file.\n", key);
    printf("%s : %d\n", key, int_value);

    config_destroy(&config);
    return 0;
}
