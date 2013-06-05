#include <stdio.h>
#include <stdlib.h>
#include "double_list.h"

/**
* DL_TABLEの作成
* 
* @return 作成したDL_TABLE*
*/
DL_TABLE *dl_table_new() {
	DL_TABLE *new = (DL_TABLE*)malloc(sizeof(DL_TABLE));

	if(new == NULL) {
		printf("Out of memory\n");
		exit(1);
	} else {
		new->top = new->end = NULL;
		new->count = 0;
		return new;
	}
}

/**
* DL_TABLEの破棄
* 
* @param:table 破棄対象のDL_TABLE*
*/
void dl_table_destroy(DL_TABLE *table) {
	DL_NODE *list = table->top, *next;
	// 末尾になるまでリストを走査
	for(; list != NULL; list = next) {
		next = list->next;
		dl_node_destroy(list);
	}
	free(table);
}

/**
* DL_NODEを動的確保します
*
* 確保されたDL_NODE*のメモリ管理を行なってください.
*
* @return 確保したDL_NODEのポインタ
*/
DL_NODE *dl_node_new() {
	DL_NODE *p = (DL_NODE*)malloc(sizeof(DL_NODE));

	if(p == NULL) {
		printf("Out of memory\n");
		exit(1);
	} else return p;
}

/**
* DL_NODEの解放
*
* 動的確保されたDL_NODEを解放します
*
* @param:node 解放するノード
*/
void dl_node_destroy(DL_NODE *node) {
	free(node);
}

/**
* ノードの新規追加
* 
* 指定されたリストの末尾にノードを新規追加します
*
* @param:table リスト管理構造体ポインタ DL_TABLE*
* @param:object 追加オブジェクト
*/
void dl_add(DL_TABLE *table, void *object) {
	DL_NODE *new = dl_node_new();
	new->object = object;

	dl_insert(table, table->end, new);
}

/**
* ノードの挿入
* 
* 指定されたノードの次に要素を挿入します
*
* @param:table リスト管理構造体ポインタ DL_TABLE*
* @param:pos 格納位置 NULLは先頭
* @param:node 格納するノードのポインタ
*
*/
void dl_insert(DL_TABLE *table, DL_NODE *pos, DL_NODE *node) {
	node->prev = pos;
	
	if(pos) { //先頭ノードでない
		node->next = pos->next;
		
		// 次のノードを更新
		if(pos->next) pos->next->prev = node;
		else table->end = node; // 末尾への挿入

		// 前のノードを更新
		pos->next = node;
	} else { // 先頭ノードである
		node->next = table->top;

		if(table->top) table->top->prev = node;
		else table->end = node;
		table->top = node;
	}


	table->count++;
}

/**
* ノードの取り除き
*
* 指定されたノードを取り除きます
* freeはされない
*
* @param:table リスト管理構造体ポインタ DL_TABLE*
* @param:node 削除するノード
*/
void dl_eliminate(DL_TABLE *table, DL_NODE *node) {
	if(node->prev) node->prev->next = node->next;
	else table->top = node->next;

	if(node->next) node->next->prev = node->prev;
	else table->end = node->prev;

	table->count--;
}

/**
* DL_TABLEのソート
* 
* DL_TABLE内のリストをソートする
*
* @param:table リスト管理構造体ポインタ DL_TABLE*
* @param:eval 評価関数へのポインタ
*
* @return ソート後のtopのノード
*/
DL_NODE *dl_sort(DL_TABLE *table, BOOL (*eval)(DL_NODE *n1, DL_NODE *n2)) {
	DL_NODE *current, *tmp, *tmp_next;
	
	// リストが空のときはNULLを返す
	if(table->top == NULL) return NULL;

	// 2番目の要素から
	for(current = table->top->next; current != NULL; current = current->next) {
		// １つ前の要素と比較して、ソートできていない時
		if((*eval)(current, current->prev)) {
			tmp = current;
			// 挿入位置を探す
			do tmp = tmp->prev; while(tmp != NULL && (*eval)(current, tmp));
			// 次の開始を記憶
			tmp_next = current->prev;
			// 移動
			dl_eliminate(table, current);
			dl_insert(table, tmp, current);
			// 次の開始をセット
			current = tmp_next;
		}
	}

	return table->top;
}

/**
* ノードの探索
*
* ノードを探索する。
* 見つからない場合NULLを返す。
*
* @param:table リストテーブル
* @param:eval  評価関数
* @param:value 評価関数に渡す評価値へのポインタ
*
* @return 一致ノードのDL_NODE*ポインタ
*/
DL_NODE *dl_search(DL_TABLE *table, BOOL (*eval)(DL_NODE *node, void *val), void *val) {
	DL_NODE *current;
	// 先頭から順に線形探索
	for(current = table->top; current != NULL; current = current->next) {
		if((*eval)(current, val)) break;
	}

	return current;
}
