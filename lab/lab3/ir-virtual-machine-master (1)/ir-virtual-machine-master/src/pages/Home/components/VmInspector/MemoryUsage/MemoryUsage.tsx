import React from "react";
import { useIntl } from "react-intl";
import { Progress } from "antd";
import styles from "./MemoryUsage.module.scss";
import { toKiB } from "@/modules/utils";

interface MemoryUsageProps {
    title: string;
    usedBytes: number;
    totalBytes: number;
    peakBytes: number;
}

const MemoryUsage: React.FC<MemoryUsageProps> = (props: MemoryUsageProps) => {
    const intl = useIntl();

    return (
        <div className={styles.divMemoryUsageWrapper}>
            <div className={styles.divUsageBlock}>
                <Progress
                    className={styles.progress}
                    percent={(props.usedBytes / props.totalBytes) * 100}
                    showInfo={false}
                    status="normal"
                />

                <div>
                    <label>{props.title}</label>

                    <label className="percentageUsage">
                        {props.totalBytes === 0
                            ? "-.-"
                            : intl.formatMessage(
                                  { id: "PERCENTAGE_USAGE" },
                                  {
                                      percentage:
                                          (props.usedBytes / props.totalBytes) *
                                          100
                                  }
                              )}
                    </label>
                </div>
                <span>
                    {intl.formatMessage(
                        { id: "B_USAGE" },
                        {
                            used: props.usedBytes,
                            total: props.totalBytes
                        }
                    )}
                </span>
                <span>
                    {intl.formatMessage(
                        { id: "KB_USAGE" },
                        {
                            used: toKiB(props.usedBytes),
                            total: toKiB(props.totalBytes)
                        }
                    )}
                </span>
            </div>

            <div className={styles.divUsageBlock}>
                <Progress
                    className={styles.progress}
                    percent={(props.peakBytes / props.totalBytes) * 100}
                    showInfo={false}
                    status="exception"
                />

                <div>
                    <label>
                        {intl.formatMessage({
                            id: "PEAK_MEMORY_USAGE"
                        })}
                    </label>

                    <label className="percentageUsage">
                        {props.totalBytes === 0
                            ? "-.-"
                            : intl.formatMessage(
                                  { id: "PERCENTAGE_USAGE" },
                                  {
                                      percentage:
                                          (props.peakBytes / props.totalBytes) *
                                          100
                                  }
                              )}
                    </label>
                </div>

                <span>
                    {intl.formatMessage(
                        { id: "BYTES" },
                        {
                            bytes: props.peakBytes
                        }
                    )}
                </span>

                <span>
                    {intl.formatMessage(
                        { id: "KB" },
                        {
                            kb: toKiB(props.peakBytes)
                        }
                    )}
                </span>
            </div>
        </div>
    );
};

export default MemoryUsage;
