#include <glib.h>
#include <stdio.h>

#define LINE_LEN 80

struct MyPair {
    gchar *key;
    int val;
};

int list_comparator(struct MyPair* first, struct MyPair* second) {
    if (first->val > second->val) {
        return -1;
    } else if (first->val < second->val) {
        return 1;
    } else {
        return g_strcmp0(first->key, second->key);
    }
}

void answer_printer(struct MyPair *elem, char *format_string) {
    if (elem == NULL) {
        return;
    }
    printf(format_string, elem->key, elem->val);
}

void list_free_func(struct MyPair *elem) {
    g_free(elem->key);
    g_free(elem);
}

void key_destroy_func(gpointer ptr) {
    g_free((gchar*)ptr);
}

void map_value_retriever(gpointer key, gpointer val_ptr, GList **list) {
    struct MyPair *pair = g_malloc(sizeof(*pair));
    pair->key = g_strdup(key);
    pair->val = GPOINTER_TO_INT(val_ptr);
    *list = g_list_append(*list, (gpointer)pair);
}

int main() {
    GHashTable *map = g_hash_table_new_full(g_str_hash, g_str_equal,
                                            (GDestroyNotify)key_destroy_func, NULL);
    char buf[LINE_LEN + 1];
    while (fgets(buf, LINE_LEN + 1, stdin) != NULL) {
        gchar **splitted_line = g_strsplit_set(buf, " \n", 0);
        gchar **cur_word_ptr = splitted_line;
        while (*cur_word_ptr != NULL) {
            if (g_strcmp0(*cur_word_ptr, "") == 0) {
                ++cur_word_ptr;
                continue;
            }
            gpointer prev_cnt_ptr = g_hash_table_lookup(map, *cur_word_ptr);
            if (prev_cnt_ptr == NULL) {
                g_hash_table_insert(map, g_strdup(*cur_word_ptr), GINT_TO_POINTER(1));
            } else {
                int prev_cnt = GPOINTER_TO_INT(prev_cnt_ptr);
                g_hash_table_replace(map, g_strdup(*cur_word_ptr), GINT_TO_POINTER(prev_cnt + 1));
            }
            ++cur_word_ptr;
        }
        g_strfreev(splitted_line);
    }
    GList *list = NULL;
    g_hash_table_foreach(map, (GHFunc)map_value_retriever, &list);
    list = g_list_sort(list, (GCompareFunc)list_comparator);
    g_list_foreach(list, (GFunc)answer_printer, "%s: %d\n");

    g_list_free_full(list, (GDestroyNotify)(list_free_func));
    g_hash_table_destroy(map);
    return 0;
}
