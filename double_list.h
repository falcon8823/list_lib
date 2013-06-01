/*! 論理型 */
typedef unsigned char BOOL;

/**
* 双方向リストノード構造体
*/
typedef struct _DL_NODE {
	void *object; /*! 格納オブジェクトのポインタ */
	struct _DL_NODE *next; /*! 次のノード */
	struct _DL_NODE *prev; /*! 前のノード */
} DL_NODE;

/**
* 双方向リスト管理構造体
*/
typedef struct _DL_TABLE {
	DL_NODE *top; /*! 先頭ノード */
	DL_NODE *end; /*! 末尾ノード */
	unsigned long count; /*! 要素数 */
} DL_TABLE;


DL_TABLE *dl_table_new();
void dl_table_destroy(DL_TABLE *table);

DL_NODE *dl_node_new(void);
void dl_insert(DL_TABLE *table, DL_NODE *pos, DL_NODE *node);
void dl_eliminate(DL_TABLE *table, DL_NODE *node);
DL_NODE *dl_sort(DL_TABLE *table, BOOL (*eval)(DL_NODE *n1, DL_NODE *n2));
void dl_add(DL_TABLE *table, void *object);
void dl_node_destroy(DL_NODE *node);
DL_NODE *dl_search(DL_TABLE *table, BOOL (*eval)(DL_NODE *node, void *val), void *val);
