# Create esc_sender.sh
#!/bin/bash
sleep 2
WID=$(xdotool search --name "cub3D" 2>/dev/null | head -1)
if [ ! -z "$WID" ]; then
    xdotool windowfocus $WID
    sleep 0.1
    xdotool key Escape
    echo "ESC sent to window $WID"
else
    echo "No cub3D window found"
fi
