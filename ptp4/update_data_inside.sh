#!/bin/bash

for app in apps/apps_inside/*.exe; do
    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)

    $app > ./data/inside_data/raw_data/size={$size}_method={$method}_{$timestamp}.txt
done