#pragma once





#include <fstream>
#include "../menu/menu_f.h"

using namespace std;

void save_suppliers_to_file(const vector<unique_ptr<supplier>>& suppliers); 
void save_shipments_to_file(const vector<unique_ptr<shipment>>& shipments);
void load_suppliers_from_file(vector<unique_ptr<supplier>>& suppliers);
void load_shipments_from_file(vector<unique_ptr<shipment>>& shipments);
