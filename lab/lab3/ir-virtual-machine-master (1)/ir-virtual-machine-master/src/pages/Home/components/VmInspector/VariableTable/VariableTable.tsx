import React, { memo } from "react";
import styles from "./VariableTable.module.scss";
import { useIntl } from "react-intl";
import type { VmVariableDetail } from "@/modules/vm/vm";
import { Table } from "antd";
import type { ColumnsType } from "antd/es/table";
import { stringCompare } from "@/modules/utils";

interface VariableTableProps {
    variables: VmVariableDetail[];
}

const VariableTable: React.FC<VariableTableProps> = memo(
    (props: VariableTableProps) => {
        const intl = useIntl();

        const columns: ColumnsType<VmVariableDetail> = [
            {
                title: intl.formatMessage({ id: "VARIABLE_ID" }),
                dataIndex: "id",
                showSorterTooltip: false,
                sorter: (a, b) => stringCompare(a.id, b.id)
            },
            {
                title: intl.formatMessage({ id: "ADDRESS" }),
                dataIndex: "address",
                showSorterTooltip: false,
                sorter: (a, b) => a.address - b.address
            },
            {
                title: intl.formatMessage({ id: "SIZE" }),
                dataIndex: "size",
                showSorterTooltip: false,
                sorter: (a, b) => a.size - b.size
            },
            {
                title: intl.formatMessage({ id: "VALUES" }),
                dataIndex: "values",
                render: (x: number[]) => (
                    <div className={styles.divValues}>
                        {x.map((y, i) => (
                            <div key={`${i}${y}`}>
                                {x.length === 1 ? (
                                    y
                                ) : (
                                    <>
                                        [{i}]: {y}
                                    </>
                                )}
                            </div>
                        ))}
                    </div>
                )
            }
        ];

        return (
            <div className={styles.divVariableTableWrapper}>
                {props.variables.length === 0 ? (
                    <div className="emptyHolder">
                        {intl.formatMessage({ id: "EMPTY_VATIABLE_TABLE" })}
                    </div>
                ) : (
                    <Table
                        rowKey="id"
                        columns={columns}
                        dataSource={props.variables}
                        size="small"
                        pagination={{
                            defaultPageSize: 20,
                            pageSizeOptions: [10, 20, 30, 50, 100],
                            showSizeChanger: true,
                            hideOnSinglePage: true,
                            size: "small"
                        }}
                    />
                )}
            </div>
        );
    }
);

export default VariableTable;
