FROM the /build/bin folder: (view in "Raw" format)


Usage: ./benchmark [options] graph_file
Options
  -aNUM [0-100] Percentage of edges allocated to CPU partition.
        The first 100-alpha of the edges is assigned the the GPUs.
        (default 50%)
  -bNUM Benchmark
     0: BFS top-down (default)
     1: PageRank
     2: SSSP
     3: Betweenness
     4: Graph500 top-down
     5: Clustering Coefficient
     6: BFS stepwise
     7: Graph500 stepwise
     8: Connected Components
  -c Creates a separate CPU partition to handle all singletons.
     (default FALSE)
  -d Sorts the edges by degree instead of by vertex id.
     (default FALSE)
  -e Swaps the direction of edge sorting to be descending order.
     (default FALSE)
  -gNUM [0-1] Number of GPUs to use. This is applicable for GPU
        and Hybrid platforms only (default 1).
  -iNUM Partitioning Algorithm
     0: Random (default)
     1: High degree nodes on CPU
     2: Low degree nodes on CPU
  -lNUM [0-100] An additional percentage of edges assigned to the
        GPUs, the last lambda% edges are assigned. This enables
        placement of each extreme on the GPU partitions.
        (default 0%)
  -mNUM Type of memory to use for GPU-based partitions
     0: Device (default)
     1: Host as memory mapped
     2: Only the vertices array on the host
     3: Only the edges array on the host
     4: Edges array partitioned between the device and the host
  -o Enables random placement of vertices across GPU partitions
     in case of multi-GPU setups (default FALSE)
  -pNUM Platform
     0: Execute on CPU only (default)
     1: Execute on GPUs only
     2: Execute on the CPU and on the GPUs
  -q Enables mapping by sorted vertex degree during partitioning
     (default FALSE)
  -rNUM [1-1000] Number of times an experiment is repeated or sources
        used to benchmark a traversal algorithm (default 5)
  -sNUM OMP scheduling type
     1: static
     2: dynamic
     3: guided (default)
  -tNUM [1-16] Number of CPU threads to use (default 16).
  -h Print this help message
