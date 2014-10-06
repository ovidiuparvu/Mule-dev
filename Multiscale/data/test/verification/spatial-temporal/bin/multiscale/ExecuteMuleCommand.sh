#!/bin/bash

bin/Mule --logic-queries "data/test/verification/spatial-temporal/bin/multiscale/queries/queries_32.in" --spatial-temporal-traces "data/test/verification/spatial-temporal/bin/multiscale/traces_32" --extra-evaluation-time 0 --model-checker-type 3 --type-semantics-table "data/test/verification/spatial-temporal/bin/multiscale/type_semantics_table/type_semantics_table.xml" --bayesian-alpha 1 --bayesian-beta 1 --bayes-factor-threshold 10000
