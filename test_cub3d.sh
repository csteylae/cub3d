#!/bin/bash

# Script simple pour tester cub3D
# Les maps dans valid_map/ doivent réussir
# Les maps dans invalid_map/ doivent échouer

echo "=== TEST CUB3D ==="
echo

# Vérifier que cub3D existe
if [ ! -f "./cub3D" ]; then
    echo "❌ cub3D pas trouvé ! Compile d'abord avec 'make'"
    exit 1
fi

echo "✅ cub3D trouvé"
echo

# Test des maps valides
echo "🟢 TEST DES MAPS VALIDES:"
for map in map/valid_map/*.cub; do
    if [ -f "$map" ]; then
        nom=$(basename "$map")
        echo -n "  $nom ... "
        
        # Lancer cub3D sur la map (en silence)
        ./cub3D "$map" > /dev/null 2>&1
        
        # Vérifier le résultat
        if [ $? -eq 0 ]; then
            echo "✅ OK"
        else
            echo "❌ FAIL"
        fi
    fi
done

echo

# Test des maps invalides  
echo "🔴 TEST DES MAPS INVALIDES:"
for map in map/invalid_map/*.cub; do
    if [ -f "$map" ]; then
        nom=$(basename "$map")
        echo -n "  $nom ... "
        
        # Lancer cub3D sur la map (en silence)
        ./cub3D "$map" > /dev/null 2>&1
        
        # Vérifier le résultat (ici on VEUT une erreur)
        if [ $? -eq 0 ]; then
            echo "❌ FAIL (devrait échouer)"
        else
            echo "✅ OK (erreur attendue)"
        fi
    fi
done

echo
echo "=== FIN DES TESTS ==="
