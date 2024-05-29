#!/bin/bash


# Удаление всех данных и папок в которых они лежат
rm -f ./data/inside_data/raw_data/*txt
rm -f ./data/inside_ticks_data/raw_data/*txt
rm -f ./data/outside_data/raw_data/*txt
rm -f ./data/inside_data/preproced_data/*txt
rm -f ./data/inside_ticks_data/preproced_data/*txt
rm -f ./data/outside_data/preproced_data/*txt
rm -f ./graphs/*
rm -rf ./apps/apps_inside
rm -rf ./apps/apps_inside_ticks
rm -rf ./apps/apps_outside
rm -rf ./data/inside_data
rm -rf ./data/inside_ticks_data
rm -rf ./data/outside_data

