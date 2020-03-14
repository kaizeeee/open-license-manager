/*
 * hw_identifier_facade.cpp
 *
 *  Created on: Dec 26, 2019
 *      Author: devel
 */

#include "hw_identifier_facade.hpp"

#include <cstdlib>
#include <stdexcept>

#include "../base/base.h"
#include "../base/logger.h"
#include "../os/cpu_info.hpp"
#include "../os/execution_environment.hpp"
#include "identification_strategy.hpp"
#include "hw_identifier.hpp"

namespace license {
namespace hw_identifier {

using namespace std;

LCC_EVENT_TYPE HwIdentifierFacade::validate_pc_signature(const std::string& str_code) {
	HwIdentifier pc_id(str_code);
	LCC_API_IDENTIFICATION_STRATEGY id_strategy = pc_id.get_identification_strategy();
	LCC_EVENT_TYPE result = IDENTIFIERS_MISMATCH;
	try {
		unique_ptr<IdentificationStrategy> strategy = IdentificationStrategy::get_strategy(id_strategy);
		result = strategy->validate_identifier(pc_id);
	} catch (logic_error& e) {
		LOG_ERROR("Error validating identifier %s: %s", str_code.c_str(), e.what());
	}
	return result;
}

std::string HwIdentifierFacade::generate_user_pc_signature(LCC_API_IDENTIFICATION_STRATEGY strategy) {
	bool use_env_var = false;
	vector<LCC_API_IDENTIFICATION_STRATEGY> strategies_to_try;
	if (strategy == STRATEGY_DEFAULT) {
		char* env_var_value = getenv(LCC_IDENTIFICATION_STRATEGY_ENV_VAR);
		if (env_var_value != nullptr && env_var_value[0] != '\0') {
			int strategy_int = atoi(env_var_value);
			if (strategy_int < 0 || strategy_int > 3) {
				LOG_WARN("unknown " LCC_IDENTIFICATION_STRATEGY_ENV_VAR " %s", env_var_value);
			} else {
				strategy = (LCC_API_IDENTIFICATION_STRATEGY)strategy_int;
				use_env_var = true;
			}
		}
	}

	unique_ptr<IdentificationStrategy> strategy_ptr = IdentificationStrategy::get_strategy(strategy);
	HwIdentifier pc_id;
	FUNCTION_RETURN result = strategy_ptr->identify_pc(pc_id);
	if (result != FUNC_RET_OK) {
		throw logic_error("strategy " + to_string(strategy_ptr->identification_strategy()) + " failed");
	}
	os::ExecutionEnvironment exec;
	os::VIRTUALIZATION virtualization = exec.getVirtualization();
	pc_id.set_virtual_environment(virtualization);
	pc_id.set_use_environment_var(use_env_var);
	if (virtualization != os::NONE) {
		bool isCloud = exec.is_cloud();
		if (isCloud) {
			pc_id.set_cloud_provider(exec.getCloudProvider());
		} else {
			os::CpuInfo cpu;
			pc_id.set_virtualization(cpu.getVirtualizationDetail());
		}
	}
	return pc_id.print();
}

}  // namespace hw_identifier
} /* namespace license */
