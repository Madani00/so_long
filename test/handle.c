printf("Game structure initialized: %p\n", game);
	printf("MLX initialized: %p\n", game->mlx);
	printf("Map rows: %d, columns: %d\n", game->row, game->column);
	if (!game->map)
		return (1); // Error handling
