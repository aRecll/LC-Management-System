
#pragma once

#include "manip_file.h"
#include "../menu/menu_f.h"
#include "../hierarchy/shipment.h"
#include "../hierarchy/supplier.h"
#include <algorithm>
#include <conio.h>

#include <iomanip>

#include <memory>
#include <vector>
#include <windows.h>


void search_suppliers_by_name_dynamic(const vector<unique_ptr<supplier>>& suppliers);
void search_shipments_by_date_dynamic(const vector<unique_ptr<shipment>>& shipments);
void search_by_company_name(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments);
void demo_operators();

void sort_suppliers_by_balance(vector<unique_ptr<supplier>>& suppliers);
void sort_shipments_by_date(vector<unique_ptr<shipment>>& shipments);
void perform_sorting(vector<unique_ptr<supplier>>& suppliers,
    vector<unique_ptr<shipment>>& shipments);


void add_new_suppliers(vector<unique_ptr<supplier>>& suppliers);
void add_new_shipments(vector<unique_ptr<shipment>>& shipments);

void save_all_data(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments);

