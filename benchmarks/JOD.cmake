#ADD_BENCHMARK ("JOD" COUPLED_FLOW/riv1_quad_coup "OGS_FEM")

#ADD_BENCHMARK ("JOD" COUPLED_FLOW/biFork1_coup "OGS_FEM")

ADD_BENCHMARK ("JOD" OVERLAND_FLOW/gian_quad "OGS_FEM" 1
	OVERLAND_FLOW/gian_quad_domain_OVERLAND_FLOW_quad.tec
	OVERLAND_FLOW/gian_quad_time_POINT4_OVERLAND_FLOW.tec
	OVERLAND_FLOW/gian_quad_time_POINT5_OVERLAND_FLOW.tec)

ADD_BENCHMARK ("JOD" OVERLAND_FLOW/gian_tri "OGS_FEM" 1
	OVERLAND_FLOW/gian_tri_domain_OVERLAND_FLOW_tri.tec
	OVERLAND_FLOW/gian_tri_time_POINT4_OVERLAND_FLOW.tec    
	OVERLAND_FLOW/gian_tri_time_POINT5_OVERLAND_FLOW.tec)

ADD_BENCHMARK ("JOD" OVERLAND_FLOW/govin_line "OGS_FEM" 1
	OVERLAND_FLOW/govin_line_domain_OVERLAND_FLOW_line.tec
	OVERLAND_FLOW/govin_line_time_POINT0_OVERLAND_FLOW.tec)

ADD_BENCHMARK ("JOD" OVERLAND_FLOW/govin_quad "OGS_FEM" 1
	OVERLAND_FLOW/govin_quad_domain_OVERLAND_FLOW_quad.tec
	OVERLAND_FLOW/govin_quad_time_POINT0_OVERLAND_FLOW.tec
	OVERLAND_FLOW/govin_quad_time_POINT1_OVERLAND_FLOW.tec)

ADD_BENCHMARK ("JOD" OVERLAND_FLOW/Wool_quad "OGS_FEM" 1
	OVERLAND_FLOW/Wool_quad_time_POINT1_OVERLAND_FLOW.tec)

# TF does not finish
#ADD_BENCHMARK ("JOD_LONG" COUPLED_FLOW/abdulLab "OGS_FEM")

#ADD_BENCHMARK ("JOD_LONG" COUPLED_FLOW/Wool_lines_coup "OGS_FEM")

#ADD_BENCHMARK ("JOD_LONG" COUPLED_FLOW/biFork2_coup "OGS_FEM")

#ADD_BENCHMARK ("JOD_EXCEEDING" COUPLED_FLOW/abdul "OGS_FEM")


